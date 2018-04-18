fn main() {
    let some_u8_value = 0u8;
    println!("some_u8_value = {:?}",  match some_u8_value {
        1 => "one",
        3 => "three",
        5 => "five",
        7 => "seven",
        _ => ""
    });
}
