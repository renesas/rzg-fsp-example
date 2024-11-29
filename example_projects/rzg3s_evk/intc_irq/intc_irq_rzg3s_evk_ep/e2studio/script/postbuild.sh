echo "Post build script started"

if [ -n "$BuildArtifactFileName" ]; then
  inputfilename=$BuildArtifactFileName
fi
if [ -n "$BUILDARTIFACTFILENAME" ]; then
  inputfilename=$BUILDARTIFACTFILENAME
fi

filebody=${inputfilename%.*}

arm-none-eabi-objcopy -O binary -j .text.secure_vector ${inputfilename} ${filebody}_secure_vector.bin
arm-none-eabi-objcopy -O binary -j .text.non_secure_vector ${inputfilename} ${filebody}_non_secure_vector.bin
arm-none-eabi-objcopy -O binary -j .text.secure_code ${inputfilename} ${filebody}_secure_code.bin
arm-none-eabi-objcopy -O binary -j .text.non_secure_code -j .data ${inputfilename} ${filebody}_non_secure_code.bin

arm-none-eabi-objcopy -O binary ${filebody}.elf -R .rodata.bootparam ${filebody}.bin
arm-none-eabi-objcopy -I binary -O srec --srec-forceS3 --adjust-vma 0x23000 ${filebody}.bin ${filebody}.srec
arm-none-eabi-objcopy -O binary ${filebody}.elf ${filebody}.bin
arm-none-eabi-objcopy -I binary -O srec --srec-forceS3 --adjust-vma 0x22D00 ${filebody}.bin ${filebody}_cm33boot.srec
rm ${filebody}.bin

echo "Post build script complete"
