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

echo "Post build script complete"
