#include "FastPix3D.h"
#include <fstream>
#include <exception>

File::File(FILE *filePtr)
{
	FilePtr = filePtr;
}

bool File::Exists(string path)
{
    if (FILE* file = fopen(path.c_str(), "r")) {
        fclose(file);
        return true;
    } else {
        return false;
    }
}
void File::Delete(string path)
{
  throw std::runtime_error("");
}
File File::OpenRead(string path)
{
	FILE *filePtr;
	if ((filePtr = fopen(path.c_str(), "rb")))
	return File(filePtr);
  else throw std::runtime_error("");
}

File File::Create(string path)
{
	FILE *filePtr;
	if (!(filePtr = fopen(path.c_str(), "wb"))) throw std::runtime_error("");
	if (filePtr == NULL) throw std::runtime_error("");
	return File(filePtr);
}
File File::Open(string path)
{
	FILE *filePtr;
	if (!(filePtr = fopen(path.c_str(), "rb"))) throw std::runtime_error("");
	return File(filePtr);
}

int64 File::getPosition()
{
	return (int64)ftello(FilePtr);
}

int32 File::Read(void *dest, int32 elementSize, int32 elementCount)
{
	int32 ret = int32(fread(dest, elementSize, elementCount, FilePtr));
	if (ferror (FilePtr))
	{
			fprintf (stderr,"Error reading file\n");
			throw std::runtime_error("Error reading file");
		}

	if (feof(FilePtr))
	{
				fprintf (stderr,"End-of-File reached.");;
				throw std::runtime_error("End-of-File reached.");
				}
	return ret;
}
sbyte File::ReadSByte()
{
	sbyte ret = fgetc(FilePtr);
	if (ret == -1) throw std::runtime_error("");
	return ret;
}
int16 File::ReadInt16()
{
	int16 ret;
	if (Read(&ret, 2, 1) != 1) throw std::runtime_error("");
	return ret;
}
int32 File::ReadInt32()
{
	int32 ret;
	if (Read(&ret, 4, 1) != 1) throw std::runtime_error("");
	return ret;
}
int64 File::ReadInt64()
{
	int64 ret;
	if (Read(&ret, 8, 1) != 1) throw std::runtime_error("");
	return ret;
}
float File::ReadFloat()
{
	float ret;
	if (Read(&ret, 4, 1) != 1) throw std::runtime_error("");
	return ret;
}
double File::ReadDouble()
{
	double ret;
	if (Read(&ret, 8, 1) != 1) throw std::runtime_error("");
	return ret;
}
byte File::ReadByte()
{
	byte ret = (byte)fgetc(FilePtr);
	if ((int)ret == -1) throw std::runtime_error("Byte read fail");
	return ret;
}
char File::ReadChar()
{
	char ret = fgetc(FilePtr);
	if (ret == (char)-1) throw std::runtime_error("Char read fail");
	return ret;
}
uint16 File::ReadUInt16()
{
	uint16 ret;
	//Read(&ret, 2, 1);
	int err = Read(&ret, 2, 1l);

	if (err != 1) throw std::runtime_error("UInt16 read fail");
	return ret;
}
uint32 File::ReadUInt32()
{
	uint32 ret;
	if (Read(&ret, 4, 1) != 1) throw std::runtime_error("");
	return ret;
}
uint64 File::ReadUInt64()
{
	uint64 ret;
	if (Read(&ret, 8, 1) != 1) throw std::runtime_error("");
	return ret;
}
string File::ReadString()
{
	char ch;
	string ret = "";
	while ((int)((ch = fgetc(FilePtr))) > -1)
	{
		if (ch == '\0') break;
		ret += ch;
	}
	return ret;
}
string File::ReadLine()
{
	char *lineChars = new char[4096];
	char *linePtr = fgets(lineChars, 4096, FilePtr);
	if (linePtr == NULL)
	{
		delete lineChars, linePtr;
		throw std::runtime_error("");
	}
	string line = string(linePtr);
	delete lineChars, linePtr;

	int32 length = int32(line.length());
	if (length > 0 && line[length - 1] == '\n')
	{
		line = line.substr(0, length - 1);
		length = int32(line.length());
		if (length > 0 && line[length - 1] == '\r') line = line.substr(0, length - 1);
	}

	return line;
}

void File::Write(void *data, int32 elementSize, int32 elementCount)
{
	fwrite(data, elementSize, elementCount, FilePtr);
}
void File::WriteSByte(sbyte value)
{
	if (fputc(value, FilePtr) == -1) throw std::runtime_error("");
}
void File::WriteInt16(int16 value)
{
	if (fwrite(&value, 2, 1, FilePtr) != 1) throw std::runtime_error("");
}
void File::WriteInt32(int32 value)
{
	if (fwrite(&value, 4, 1, FilePtr) != 1) throw std::runtime_error("");
}
void File::WriteInt64(int64 value)
{
	if (fwrite(&value, 8, 1, FilePtr) != 1) throw std::runtime_error("");
}
void File::WriteFloat(float value)
{
	if (fwrite(&value, 4, 1, FilePtr) != 1) throw std::runtime_error("");
}
void File::WriteDouble(double value)
{
	if (fwrite(&value, 8, 1, FilePtr) != 1) throw std::runtime_error("");
}
void File::WriteByte(byte value)
{
	if (fputc((int)value, FilePtr) == -1) throw std::runtime_error("");
}
void File::WriteChar(char value)
{
	if (fputc(value, FilePtr) == -1) throw std::runtime_error("");
}
void File::WriteUInt16(uint16 value)
{
	if (fwrite(&value, 2, 1, FilePtr) != 1) throw std::runtime_error("");
}
void File::WriteUInt32(uint32 value)
{
	if (fwrite(&value, 4, 1, FilePtr) != 1) throw std::runtime_error("");
}
void File::WriteUInt64(uint64 value)
{
	if (fwrite(&value, 8, 1, FilePtr) != 1) throw std::runtime_error("");
}
void File::WriteString(string value)
{
	if (fputs(value.c_str(), FilePtr) < 0) throw std::runtime_error("");
	WriteChar('\0');
}
void File::WriteLine(string value)
{
	WriteString(value);
	WriteChar('\n');
}

void File::Seek(int64 position, SeekOrigin origin)
{
	fseeko(FilePtr, position, int32(origin));
}
void File::Close()
{
	fclose(FilePtr);
}
