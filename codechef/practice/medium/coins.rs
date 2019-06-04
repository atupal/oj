use std::io;
use std::collections::HashMap;

fn read_uint() -> Option<u32> {
    let mut input_text = String::new();
    io::stdin().read_line(&mut input_text).expect("failed to read from stdin");

    let trimmed = input_text.trim();
    match trimmed.parse::<u32>() {
        Ok(i) => Some(i),
        Err(..) => None,
    }
}

static mut CACHE: Option<HashMap<u32, u32>> = None;

fn solve(i: u32) -> u32 {
    unsafe{
        if let Some(ref _cache) = CACHE {
            if let Some(v) = _cache.get(&i) {
                return *v;
            }
        }
    };

    let answer = {
        if i < 12 {
            i
        } else {
            let i_2 = solve(i / 2);
            let i_3 = solve(i / 3);
            let i_4 = solve(i / 4);
            if i_2 + i_3 + i_4 > i {
                i_2 + i_3 + i_4
            } else {
                i
            }
        }
    };

    unsafe{
        if let Some(ref mut _cache) = CACHE {
            if i < 10000000 {
                _cache.insert(i, answer);
            }
        }
    };

    answer
}

fn main() {
    unsafe {
        CACHE = Some(HashMap::new());
    }

    loop {
        let read_result = read_uint();
        match read_result {
            Some(i) => println!("{}", solve(i)),
            None => break,
        }
    }
}
