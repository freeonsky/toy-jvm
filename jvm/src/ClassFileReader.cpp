#include "../include/ClassFileReader.h"
#include "../include/DataInputStream.h"

static cp_info * readCpInfo(DataInputStream &dis) {
	cp_info* info = new cp_info();
	info->tag = dis.readU1();
	switch (info->tag) {
	case CONSTANT_Class:
		info->info.class_info.name_index = dis.readU2();
		break;
	case CONSTANT_Fieldref:
		info->info.fieldref_info.class_index = dis.readU2();
		info->info.fieldref_info.name_and_type_index = dis.readU2();
		break;
	case CONSTANT_Methodref:
		info->info.methodref_info.class_index = dis.readU2();
		info->info.methodref_info.name_and_type_index = dis.readU2();
		break;
	case CONSTANT_InterfaceMethodref:
		info->info.interfaceMethodref_info.class_index = dis.readU2();
		info->info.interfaceMethodref_info.name_and_type_index = dis.readU2();
		break;
	case CONSTANT_String:
		info->info.string_info.string_index = dis.readU2();
		break;
	case CONSTANT_Integer:
		info->info.integer_info.bytes = dis.readU4();
		break;
	case CONSTANT_Float:
		info->info.float_info.bytes = dis.readU4();
		break;
	case CONSTANT_Long:
		info->info.long_info.high_bytes = dis.readU4();
		info->info.long_info.low_bytes = dis.readU4();
		break;
	case CONSTANT_Double:
		info->info.double_info.high_bytes = dis.readU4();
		info->info.double_info.low_bytes = dis.readU4();
		break;
	case CONSTANT_NameAndType:
		info->info.nameAndType_info.name_index = dis.readU2();
		info->info.nameAndType_info.descriptor_index = dis.readU2();
		break;
	case CONSTANT_Utf8:
		info->info.utf8_info.length = dis.readU2();
		info->info.utf8_info.bytes = new u1[info->info.utf8_info.length];
		for (int i = 0; i < info->info.utf8_info.length; i++) {
			info->info.utf8_info.bytes[i] = dis.readU1();
		}
		break;
	}
	return info;
}

static field_info* readFieldInfo(DataInputStream &dis) {
	field_info* info = new field_info();

	return info;
}

static method_info* readMethodInfo(DataInputStream &dis) {
	method_info* info = new method_info();

	return info;
}

static attribute_info* readAttributeInfo(DataInputStream &dis) {
	attribute_info* info = new attribute_info();

	return info;
}


ClassFileReader::ClassFileReader()
{
}


ClassFileReader::~ClassFileReader()
{
}

ClassFile* ClassFileReader::readClassFile(std::istream & is)
{
	ClassFile *cf = new ClassFile();
	DataInputStream dis(is);
	cf->magic = dis.readU4();
	cf->minor_version = dis.readU2();
	cf->major_version = dis.readU2();

	cf->constant_pool_count = dis.readU2();
	cf->constant_pool = new cp_info *[cf->constant_pool_count-1];
	for (int i = 0; i < cf->constant_pool_count - 1; i++) {
		cf->constant_pool[i] = readCpInfo(dis);
	}

	cf->access_flags = dis.readU2();
	cf->this_class = dis.readU2();
	cf->super_class = dis.readU2();

	cf->interfaces_count = dis.readU2();	
	cf->interfaces = new u2[cf->interfaces_count];
	for (int i = 0; i < cf->interfaces_count; i++) {
		cf->interfaces[i] = dis.readU2();
	}
	
	cf->fields_count = dis.readU2();
	cf->fields = new field_info*[cf->fields_count];
	for (int i = 0; i < cf->fields_count; i++) {
		cf->fields[i] = readFieldInfo(dis);
	}

	cf->methods_count = dis.readU2();
	cf->methods = new method_info*[cf->methods_count];
	for (int i = 0; i < cf->methods_count; i++) {
		cf->methods[i] = readMethodInfo(dis);
	}

	cf->attributes_count = dis.readU2();
	cf->attributes = new attribute_info*[cf->attributes_count];
	for (int i = 0; i < cf->attributes_count; i++) {
		cf->attributes[i] = readAttributeInfo(dis);
	}

	return cf;
}
