use std::{fs};

fn main() {
    let mut file = get_file_contents("../../test.pr");
    remove_comments(&mut file);
    let lines = split_file_into_lines(file);
    for line in &lines {
        let tokens = tokenize(&line);
        serve_keyword_token(&tokens);
    }
    // let mut test = String::new(); std::io::stdin().read_line(&mut test); // for leaks
}

fn serve_keyword_token(tokens: &Vec<String>) {
    let tokens = remove_whitespace_tokens(tokens);
    if !tokens.is_empty() {
        match tokens[0].as_str() {
            "print" => print!("{}", tokens[1]),
            "puts" => println!("{}", tokens[1]),
            "let" => println!("I'm in the `let` branch"),
            "for" => println!("I'm in the `for` branch"),
            "if" => println!("I'm in the `if` branch"),
            _ => println!("This line doesn't have a keyword"),
        }
    }
}

fn trim_leading_whitespace(token: &String) -> String {
    token.trim_start().to_string()
}

fn remove_whitespace_tokens(tokens: &Vec<String>) -> Vec<String> {
    let mut new_vec = Vec::<String>::new();
    for token in tokens {
        let token = trim_leading_whitespace(&token);
        if token.is_empty() || token == " " {
            continue;
        }
        new_vec.push(token.to_owned());
    }
    new_vec
}

fn split_file_into_lines(file: String) -> Vec<String> {
    file
        .split("\n")
        .collect::<Vec<&str>>()
        .into_iter()
        .map(|line| line.to_string())
        .collect::<Vec<String>>()
}

fn contains_valid_string(line: &String) -> bool {
    let quotes = {
        line
            .chars()
            .filter(|c| c == &'"')
            .collect::<Vec<char>>()
    };
    quotes.len() >= 2
}

fn tokenize_string(line: &String, start_index: usize) -> String {
    let mut result_string = String::new();
    for i in start_index..line.len()-2 {
        let c = {
            &line
                .chars()
                .nth(i)
                .unwrap()
        };
        let next = {
            &line
                .chars()
                .nth(i+1)
                .unwrap()
        };
        if next == &'"' && c != &'\\' {
            break;
        }
        if c == &'\\' && next == &'n' {
            result_string += "\n";
            continue;
        }
        if next != &'\\' {
            result_string += &next.to_string();
        }
    }
    result_string
}

fn tokenize_string_line(tokens: &mut Vec<String>, line: &String) {
    let index = line.find("\"").unwrap();
    let internal_string = tokenize_string(&line, index);
    let mut token = String::new();
    for c in line.chars() {
        if c == '"' { 
            break;
        }
        if c == ' ' {
            tokens.push(token);
            token = String::from("");
        }
        token += &c.to_string().as_str();
    }
    tokens.push(internal_string);
}

fn tokenize_non_string_line(tokens: &mut Vec<String>, line: &String) {
    let mut token = String::new();
    for c in line.chars() {
        if c == ' ' {
            tokens.push(token);
            token = String::from("");
        }
        token += &c.to_string().as_str();
    }
    tokens.push(token);
}

fn tokenize(line: &String) -> Vec<String> {
    let mut tokens = Vec::<String>::new();
    if contains_valid_string(&line) {
        tokenize_string_line(&mut tokens, line);
    }
    else {
        tokenize_non_string_line(&mut tokens, line);
    }
    tokens
}

fn remove_comments(file: &mut String) {
    let mut new_file = String::new();
    for line in file.lines() {
        let new_line;
        if let Some(i) = line.find("//") {
            new_line = line[0..i].to_string() + "\n";
            new_file.push_str(&new_line)
        }
        else {
            new_line = line.to_string() + "\n";
            new_file.push_str(&new_line);
        }
    }
    *file = new_file;
}

fn get_file_contents(path: &str) -> String {
    let contents = fs::read_to_string(path);
    match contents {
        Ok(file) => file,
        Err(_)   => String::new(),
    }
}

#[allow(dead_code)]
fn greet() {
    println!(
        "Welcome to the main compilation environment for the `Prog` Programming Language!"
    );
    println!("Rust will eventually be the primary language that Prog is implemented in,
so this will serve as the central hub for the project.");
}
