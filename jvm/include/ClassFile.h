#ifndef CLASS_FILE_H
#define CLASS_FILE_H


#include <cstdint>

typedef uint8_t u1;
typedef uint16_t u2;
typedef uint32_t u4;

typedef struct cp_info				cp_info;
typedef struct field_info			field_info;
typedef struct method_info			method_info;
typedef struct attribute_info		attribute_info;
typedef struct exception_info		exception_info;
typedef struct classes_info			classes_info;
typedef struct line_number_info		line_number_info;
typedef struct local_variable_info	local_variable_info;


struct ClassFile
{
	u4				magic;
	u2				minor_version;
	u2				major_version;
	u2				constant_pool_count;
	// constant_pool[constant_pool_count - 1]
	cp_info			**constant_pool;
	u2				access_flags;
	u2				this_class;
	u2				super_class;
	u2				interfaces_count;
	// interfaces[interfaces_count]
	u2				*interfaces;
	u2				fields_count;
	// fields[fields_count]
	field_info		**fields;
	u2				methods_count;
	// methods[methods_count]
	method_info		**methods;
	u2				attributes_count;
	// attributes[attributes_count]
	attribute_info	**attributes;
};

enum AccessFlag {
	ACC_PUBLIC = 0x0001,
	ACC_FINAL = 0x0010,
	ACC_SUPER = 0x0020,
	ACC_INTERFACE = 0x0200,
	ACC_ABSTRACT = 0x0400
};

enum ConstantType {
	CONSTANT_Class = 7,
	CONSTANT_Fieldref = 9,
	CONSTANT_Methodref = 10,
	CONSTANT_InterfaceMethodref = 11,
	CONSTANT_String = 8,
	CONSTANT_Integer = 3,
	CONSTANT_Float = 4,
	CONSTANT_Long = 5,
	CONSTANT_Double = 6,
	CONSTANT_NameAndType = 12,
	CONSTANT_Utf8 = 1
};

typedef struct CONSTANT_Class_info {
	u2 name_index;
} CONSTANT_Class_info;

typedef struct CONSTANT_Fieldref_info {
	u2 class_index;
	u2 name_and_type_index;
} CONSTANT_Fieldref_info;

typedef struct CONSTANT_Methodref_info {
	u2 class_index;
	u2 name_and_type_index;
} CONSTANT_Methodref_info;

typedef struct CONSTANT_InterfaceMethodref_info {
	u2 class_index;
	u2 name_and_type_index;
} CONSTANT_InterfaceMethodref_info;

typedef struct CONSTANT_String_info {
	u2 string_index;
} CONSTANT_String_info;

typedef struct CONSTANT_Integer_info {
	u4 bytes;
} CONSTANT_Integer_info;

typedef struct CONSTANT_Float_info {
	u4 bytes;
} CONSTANT_Float_info;

typedef struct CONSTANT_Long_info {
	u4 high_bytes;
	u4 low_bytes;
} CONSTANT_Long_info;

typedef struct CONSTANT_Double_info {
	u4 high_bytes;
	u4 low_bytes;
} CONSTANT_Double_info;

typedef struct CONSTANT_NameAndType_info {
	u2 name_index;
	u2 descriptor_index;
} CONSTANT_NameAndType_info;

typedef struct CONSTANT_Utf8_info {
	u2 length;
	u1 *bytes;
} CONSTANT_Utf8_info;

typedef struct cp_info {
	u1 tag;
	union {
		CONSTANT_Class_info                 class_info;
		CONSTANT_Fieldref_info              fieldref_info;
		CONSTANT_Methodref_info             methodref_info;
		CONSTANT_InterfaceMethodref_info    interfaceMethodref_info;
		CONSTANT_String_info                string_info;
		CONSTANT_Integer_info               integer_info;
		CONSTANT_Float_info                 float_info;
		CONSTANT_Long_info                  long_info;
		CONSTANT_Double_info                double_info;
		CONSTANT_NameAndType_info           nameAndType_info;
		CONSTANT_Utf8_info                  utf8_info;
	} info;
} cp_info;

//--------------------------------- jvm 8 start --------------------------
typedef struct CONSTANT_MethodHandle_info {
	u1 tag; // 15
	u1 reference_kind;
	u2 reference_index;
} CONSTANT_MethodHandle_info;

typedef struct CONSTANT_MethodType_info {
	u1 tag; // 16
	u2 descriptor_index;
} CONSTANT_MethodType_info;

typedef struct CONSTANT_InvokeDynamic_info {
	u1 tag; // 18
	u2 bootstrap_method_attr_index;
	u2 name_and_type_index;
} CONSTANT_InvokeDynamic_info;
//--------------------------------- jvm 8 end --------------------------

typedef struct field_info {
	u2				access_flags;
	u2				name_index;
	u2				descriptor_index;
	u2				attributes_count;
	// attributes[attributes_count]
	attribute_info	**attributes;
} field_info;

typedef struct method_info {
	u2				access_flags;
	u2				name_index;
	u2				descriptor_index;
	u2				attributes_count;
	// attributes[attributes_count]
	attribute_info	**attributes;
} method_info;



typedef struct ConstantValue_attribute {
	u4 attribute_length;
	u2 constantvalue_index;
} ConstantValue_attribute;

typedef struct Code_attribute {
	u4 attribute_length;
	u2				max_stack;
	u2				max_locals;
	u4				code_length;
	//				code[code_length]
	u1				*code;
	u2				exception_table_length;
	// exception_table[exception_table_length]
	exception_info	*exception_table;
	u2				attributes_count;
	// attributes[attributes_count]
	attribute_info	**attributes;
} Code_attribute;

typedef struct Exceptions_attribute {
	u4 attribute_length;
	u2 number_of_exceptions;
	// exception_index_table[number_of_exceptions]
	u2 *exception_index_table;
} Exceptions_attribute;

typedef struct InnerClasses_attribute {
	u4 attribute_length;
	u2				number_of_classes;
	// classes[number_of_classes]
	classes_info	*classes;
} InnerClasses_attribute;

typedef struct Synthetic_attribute {
	u4 attribute_length;
} Synthetic_attribute;

typedef struct SourceFile_attribute {
	u4 attribute_length;
	u2	sourcefile_index;
} SourceFile_attribute;

typedef struct LineNumberTable_attribute {
	u4 attribute_length;
	u2					line_number_table_length;
	//line_number_table[line_number_table_length]
	line_number_info	*line_number_table;
} LineNumberTable_attribute;

typedef struct LocalVariableTable_attribute {
	u4 attribute_length;
	u2						local_variable_table_length;
	// local_variable_table[local_variable_table_length]
	local_variable_info		*local_variable_table;
} LocalVariableTable_attribute;

typedef struct Deprecated_attribute {
	u4 attribute_length;
} Deprecated_attribute;


typedef struct attribute_info {
	u2 attribute_name_index;

	// info[attribute_length]
	//u1 *info;
	union {
		ConstantValue_attribute constantValue_info;
		Code_attribute code_info;
		Exceptions_attribute exceptions_info;
		InnerClasses_attribute innerClasses_info;
		Synthetic_attribute synthetic_info;
		SourceFile_attribute sourceFile_info;
		LineNumberTable_attribute lineNumberTable_info;
		LocalVariableTable_attribute localVariable_info;
		Deprecated_attribute deprecated_info;
	} info;
} attribute_info;

typedef struct exception_info {
	u2	start_pc;
	u2	end_pc;
	u2	handler_pc;
	u2	catch_type;
} exception_info;

typedef struct classes_info {
	u2	inner_class_info_index;
	u2	outer_class_info_index;
	u2	inner_name_index;
	u2	inner_class_access_flags;
} classes_info;

typedef struct line_number_info {
	u2	start_pc;
	u2	line_number;
} line_number_info;

typedef struct local_variable_info {
	u2	start_pc;
	u2	length;
	u2	name_index;
	u2	descriptor_index;
	u2	index;
} local_variable_info;



#endif
