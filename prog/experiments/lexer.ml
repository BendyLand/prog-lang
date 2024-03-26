
let path = "../../test.pr"

let split_file_into_lines file = 
    String.split_on_char '\n' file;;

let read_file_to_string path = 
    let file = open_in_bin path in
    let str = really_input_string file (in_channel_length file) in
    close_in file;
    str;;

let result = read_file_to_string path in
split_file_into_lines result 


