use std::{fs};

fn main() {
    let mut file = get_file_contents("../../test.pr");
    remove_comments(&mut file);
    let lines = split_file_into_lines(file);
    for line in lines {
        let tokens = tokenize(&line);
        for token in tokens {
            println!("token: {}", token);
        }
    }
    // let mut test = String::new(); std::io::stdin().read_line(&mut test); // for leaks
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
    for i in start_index..line.len() {
        let c = {
            &line
                .chars()
                .nth(i)
                .unwrap_or_default()
                .to_string()
        };
        if c == &'"'.to_string() {
            break;
        }
        result_string += c;
    }
    result_string
}

fn tokenize_string_line(tokens: &mut Vec<String>, line: &String) {
    let index = line.find("\"").unwrap();
    let internal_string = tokenize_string(&line, index + 1);
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
