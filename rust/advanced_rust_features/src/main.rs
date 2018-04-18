fn main() {
    let list_of_numbers = vec![1, 2, 3];
    let answer: i32 = list_of_numbers
        .iter()
        .sum();

    println!("sum of numbers: {:?}", answer);
}
