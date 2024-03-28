keyword(if_).
keyword(for_).
keyword(let_).
keyword(print_).
keyword(puts_).

change(open_curly_brace).
change(equals).

end(arg).
end(closed_curly_brace).
end(val).

arg(expr).
arg(cond).
arg(str).
arg(range).
arg(var_name).

followed_by(keyword(if_), arg(cond), change(open_curly_brace), end(closed_curly_brace)).
followed_by(keyword(for_), arg(range), change(open_curly_brace), end(closed_curly_brace)).
followed_by(keyword(let_), arg(var_name), change(=), end(val)).
followed_by(keyword(print_), arg(str), end(arg)).
followed_by(keyword(puts_), arg(str), end(arg)).
