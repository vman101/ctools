section .data
    global expr_size
    expr_size:      dq  32

    global expr_type
    expr_type:      dq  0

    global expr_tok_cnt
    expr_tok_cnt:   dq  8

    global expr_tok
    expr_tok:       dq  16


%define EXPR_SIZE 32

; struct expression size = 32
;   .type
;   .tok_count + 8
;   .tokens + 16
