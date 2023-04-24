#!/bin/bash

# Go into the top-level directory of the repo
cd $(git rev-parse --show-toplevel)

usage() {
        echo "Usage: $0 [<NUMFILES>] [<BRANCH>]"
}

if [[ $# -gt 2 ]]; then
        usage
        exit 1
fi

# Take in number of files to check and branch to check containment in
NUMFILES=${1}
BRANCH=${2}

# Check the top 10 files by size by default
if [[ -z "$NUMFILES" ]]; then
        NUMFILES=10
fi

# Check presence in origin/main by default
if [[ -z "$BRANCH" ]]; then
        BRANCH="origin/main"
fi

# This file stores the result of pack verifications
TMPFILE=$(mktemp)

# List all the pack index files
PACK=$(ls .git/objects/pack/*.idx)

# This is the meat of the script; it finds large pack files
find_large_files() {
        # Which pack file to search
        IDXFILE=${1}
        echo -e "Searching the largest $NUMFILES object(s) in $IDXFILE...\n"
        # Verify and list objects in the pack file
        git verify-pack -v $IDXFILE > ${TMPFILE}
        # Sort and list the top NUMFILES files by size
        BLOBS=$(cat $TMPFILE | sort -k 3 -n | tail -n $NUMFILES)
        # Get the blob hashes of the files
        BLOBHASHES=$(echo "$BLOBS" | cut -d ' ' -f 1)
        # Get the sizes of the files
        BLOBSIZES=($(echo "$BLOBS" | cut -d ' ' -f 5))
        # Get the paths to the files
        BLOBPATHS=($(echo $BLOBHASHES | xargs -d ' ' -I % sh -c \
                "git rev-list --objects --all | grep %" | cut -d ' ' -f 2))
        # Convert to list
        BLOBHASHES=($BLOBHASHES)

        # Loop through each file and find its commit hash and containment in the branch
        for i in ${!BLOBHASHES[@]}; do
                # Get all commit hashes from log of the subtree associated with the file,
                # then search the contents of the subtree for the blob hash and echo this
                # if we find a match
                COMMITHASH=$(git log --all --pretty=format:%H -- ${BLOBPATHS[i]} | \
                        xargs -I % sh -c "git ls-tree % -- ${BLOBPATHS[i]} | \
                        grep -q ${BLOBHASHES[i]} && echo %")
                # Check containment in remotely-tracked branches
                BRANCHES=$(git branch -r --contains $COMMITHASH)

                # Indicate containment and print file information
                if echo "$BRANCHES" | grep -q $BRANCH; then
                        echo "File ${BLOBPATHS[i]} is referenced in commit $COMMITHASH,"\
                                "takes up $(echo "${BLOBSIZES[i]}" | numfmt --to=iec),"\
                                "and is in $BRANCH."
                else
                        echo "File ${BLOBPATHS[i]} is referenced in commit $COMMITHASH,"\
                                "takes up $(echo "${BLOBSIZES[i]}" | numfmt --to=iec),"\
                                "and is not in $BRANCH."
                fi
                echo
        done
}

# Handle multiple pack files
for PACKFILE in ${PACK[@]}; do
        find_large_files $PACKFILE
done

# Remove temporary file storage
rm ${TMPFILE}
