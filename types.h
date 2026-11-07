#ifndef TYPES_H
#define TYPES_H

typedef enum
{
    e_failure,
    e_success
} Status;

typedef enum
{
    e_view,
    e_edit,
    e_unsupported
} OperationType;
OperationType check_operation_type(char *symbol);
#endif