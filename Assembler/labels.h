#ifndef LABELS_H
#define LABELS_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <ctype.h>
#include "../SimpleStack/data_types.h"
#include "../Common/err_codes.h"
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/** @file */

#define LAB_BUF 100
#define LAB_TABLE_INIT 50

//!@typedef Typedef for LabelStr struct
typedef struct LabelStr Label;

//!@typedef Typedef for values of labels
typedef uint32_t label_t;

/**@brief  Label structure for jumps in code
 *
 * @param pos The address of label's position in code
 * @param label The name of label
 */
struct LabelStr {
    label_t pos;
    char * label;
};

int LabelTableCTor(Label ** lab_table, stk_size_t lab_num);
int LabelTableDTor(Label * lab_table, stk_size_t lab_num);
int LabelTableRLC(Label * lab_table, stk_size_t lab_num);
int ReadLabels(FILE * inp_file, Label ** lab_table, size_t * lab_count);

#endif //LABELS_H
