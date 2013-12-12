make > log.txt 2>&1
cat log.txt | grep 'error' > filtered.txt
vim filtered.txt
