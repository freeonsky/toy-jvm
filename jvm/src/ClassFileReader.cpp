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

bool utf8Equals(u1 *src, char * expected) {
	bool flag = true;
	int i = 0;
	while (expected[i]) {
		if (expected[i] != src[i]) {
			return false;
		}
		i++;
	}
	return flag;
}

static attribute_info* readAttributeInfo(DataInputStream &dis, ClassFile * cf) {
	attribute_info* info = new attribute_info();
	info->attribute_name_index = dis.readU2();
	auto bytes = cf->constant_pool[info->attribute_name_index-1]->info.utf8_info.bytes;
	if (utf8Equals(bytes, "ConstantValue")) {
		info->info.constantValue_info.attribute_length = dis.readU4();
		info->info.constantValue_info.constantvalue_index = dis.readU2();
	}
	else if (utf8Equals(bytes, "Code")) {
		info->info.code_info.attribute_length = dis.readU4();
		info->info.code_info.max_stack = dis.readU2();
		info->info.code_info.max_locals = dis.readU2();
		
		info->info.code_info.code_length = dis.readU4();
		info->info.code_info.code = new u1[info->info.code_info.code_length];
		for (int i = 0; i < info->info.code_info.code_length; i++) {
			info->info.code_info.code[i] = dis.readU1();
		}

		info->info.code_info.exception_table_length = dis.readU2();
		info->info.code_info.exception_table = new exception_info[info->info.code_info.exception_table_length];
		for (int i = 0; i < info->info.code_info.exception_table_length; i++) {
			info->info.code_info.exception_table[i].start_pc = dis.readU2();
			info->info.code_info.exception_table[i].end_pc = dis.readU2();
			info->info.code_info.exception_table[i].handler_pc = dis.readU2();
			info->info.code_info.exception_table[i].catch_type = dis.readU2();
		}
		
		info->info.code_info.attributes_count = dis.readU2();
		info->info.code_info.attributes = new attribute_info*[info->info.code_info.attributes_count];
		for (int i = 0; i < info->info.code_info.attributes_count; i++) {
			info->info.code_info.attributes[i] = readAttributeInfo(dis, cf);
		}
	}
	else if (utf8Equals(bytes, "Exceptions")) {
		info->info.exceptions_info.attribute_length = dis.readU4();
		info->info.exceptions_info.number_of_exceptions = dis.readU2();
		info->info.exceptions_info.exception_index_table = new u2[info->info.exceptions_info.number_of_exceptions];
		for (int i = 0; i < info->info.exceptions_info.number_of_exceptions; i++) {
			info->info.exceptions_info.exception_index_table[i] = dis.readU2();
		}
	}
	else if (utf8Equals(bytes, "InnerClasses")) {
		info->info.innerClasses_info.attribute_length = dis.readU4();
		info->info.innerClasses_info.number_of_classes = dis.readU2();
		info->info.innerClasses_info.classes = new classes_info[info->info.innerClasses_info.number_of_classes];
		for (int i = 0; i < info->info.innerClasses_info.number_of_classes; i++) {
			info->info.innerClasses_info.classes[i].inner_class_info_index = dis.readU2();
			info->info.innerClasses_info.classes[i].outer_class_info_index = dis.readU2();
			info->info.innerClasses_info.classes[i].inner_name_index = dis.readU2();
			info->info.innerClasses_info.classes[i].inner_class_access_flags = dis.readU2();
		}
	}
	else if (utf8Equals(bytes, "Synthetic")) {
		info->info.synthetic_info.attribute_length = dis.readU4();
	}
	else if (utf8Equals(bytes, "SourceFile")) {
		info->info.sourceFile_info.attribute_length = dis.readU4();
	}
	else if (utf8Equals(bytes, "LineNumberTable")) {
		info->info.lineNumberTable_info.attribute_length = dis.readU4();
		info->info.lineNumberTable_info.line_number_table_length = dis.readU2();
		info->info.lineNumberTable_info.line_number_table = new line_number_info[info->info.lineNumberTable_info.line_number_table_length];
		for (int i = 0; i < info->info.lineNumberTable_info.line_number_table_length; i++) {
			info->info.lineNumberTable_info.line_number_table->start_pc = dis.readU2();
			info->info.lineNumberTable_info.line_number_table->line_number = dis.readU2();
		}
	}
	else if (utf8Equals(bytes, "LocalVariableTable")) {
		info->info.localVariable_info.attribute_length = dis.readU4();
		u2 len = dis.readU2();
		info->info.localVariable_info.local_variable_table_length = len;
		info->info.localVariable_info.local_variable_table = new local_variable_info[len];
		for (int i = 0; i < len; i++) {
			info->info.localVariable_info.local_variable_table[i].start_pc = dis.readU2();
			info->info.localVariable_info.local_variable_table[i].length = dis.readU2();
			info->info.localVariable_info.local_variable_table[i].name_index = dis.readU2();
			info->info.localVariable_info.local_variable_table[i].descriptor_index = dis.readU2();
			info->info.localVariable_info.local_variable_table[i].index = dis.readU2();
		}
	
	}
	else if (utf8Equals(bytes, "Deprecated")) {
		info->info.deprecated_info.attribute_length = dis.readU4();
	}
	return info;
}

static field_info* readFieldInfo(DataInputStream &dis, ClassFile * cf) {
	field_info* info = new field_info();
	info->access_flags = dis.readU2();
	info->name_index = dis.readU2();
	info->descriptor_index = dis.readU2();
	
	info->attributes_count = dis.readU2();
	info->attributes = new attribute_info*[info->attributes_count];
	for (int i = 0; i < info->attributes_count; i++) {
		info->attributes[i] = readAttributeInfo(dis, cf);
	}
	return info;
}

static method_info* readMethodInfo(DataInputStream &dis, ClassFile * cf) {
	method_info* info = new method_info();
	info->access_flags = dis.readU2();
	info->name_index = dis.readU2();
	info->descriptor_index = dis.readU2();
	
	info->attributes_count = dis.readU2();
	info->attributes = new attribute_info*[info->attributes_count];
	for (int i = 0; i < info->attributes_count; i++) {
		info->attributes[i] = readAttributeInfo(dis, cf);
	}
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
		cf->fields[i] = readFieldInfo(dis, cf);
	}

	cf->methods_count = dis.readU2();
	cf->methods = new method_info*[cf->methods_count];
	for (int i = 0; i < cf->methods_count; i++) {
		cf->methods[i] = readMethodInfo(dis, cf);
	}

	cf->attributes_count = dis.readU2();
	cf->attributes = new attribute_info*[cf->attributes_count];
	for (int i = 0; i < cf->attributes_count; i++) {
		cf->attributes[i] = readAttributeInfo(dis, cf);
	}

	return cf;
}
