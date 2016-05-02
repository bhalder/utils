#! /bin/sh

dat=`date +%s`
filename="result"-$dat
touch $filename
# Test command_line
echo "Testing Command Line" >> $filename
echo "## No Parameter ##" >> $filename
./elf_parser >> $filename

echo "## Wrong Parameter ##" >> $filename
./elf_parser abc>> $filename

echo "## Correct Parameter ##" >> $filename
./elf_parser test_prog >> $filename
echo "## DONE ##" >> $filename

