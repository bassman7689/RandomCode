fn main() {
    let some_number = Some(5);
    let some_string = Some("a string");

    let absent_number: Option<i32> = None;

    if some_number.is_some() {
        println!("some_number   = {:?}", some_number);
    }

    if some_string.is_some() {
        println!("some_string   = {:?}", some_string);
    }

    if absent_number.is_some() {
        println!("absent_number = {:?}", absent_number);
    }
}
