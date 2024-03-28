open Printf

let path = "../../../../test.pr";;

let split_file_into_lines file = 
    String.split_on_char '\n' file;;

let read_file_to_string path = 
    let file = open_in_bin path in
    let str = really_input_string file (in_channel_length file) in
    close_in file;
    str;;

let result = read_file_to_string path in
let lines = split_file_into_lines result in
let pattern = Re.compile (Re.Perl.re "\\s*\".*\"") in 
let new_lines = 
    List.map (fun line -> 
        if String.contains line '"' then
            let embedded_str_match = Re.exec pattern line in
            let first_token = List.nth (String.split_on_char ' ' line) 0 in
            let embedded_str = Re.Group.get embedded_str_match 0 in
            [first_token; embedded_str]
        else
            String.split_on_char ' ' line
    ) lines in 

List.iter (fun line_tokens -> 
    List.iter (fun token -> 
        printf "%s\n" token) line_tokens) new_lines
