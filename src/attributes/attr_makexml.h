
#ifndef _ATTR_MAKEXML_H_
#define _ATTR_MAKEXML_H_

#include "../ds/dcontainer.h"
#include "../getFiletype/identify_extension.h"
#include "../query/query_parser.h"
#include "show_attributes.h"

void attribute_count_add( int count, container *attributes, int argc, ... );
void attribute_count_print( container *attributes, int attrib_len, int indent );
void attribute_destroy_recursive( container *attributes );

char* attribute_generate_xml(container *attributes, int attrib_len, attr_conf *showattrp, struct fte_data *getfiletypep, query_array *qa);

#endif	// _ATTR_MAKEXML_H_