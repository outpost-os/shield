// SPDX-FileCopyrightText: 2023 - 2024 Ledger SAS
//
// SPDX-License-Identifier: Apache-2.0 OR BSD-3-Clause

#ifndef LOG_LEXER_H
#define LOG_LEXER_H

#include <inttypes.h>
#include <stdbool.h>

uint8_t print_with_len(const char *fmt, va_list *args, size_t *sizew);

uint16_t log_get_dbgbuf_offset(void);
uint8_t* log_get_dbgbuf(void);
void dbgbuffer_flush(void);

#endif/*!LOG_LEXER_H*/
