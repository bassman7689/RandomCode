struct User {
    username : String,
    email: String,
    sign_in_count: u64,
    active: bool,
}

fn build_user(email: String, username: String) -> User {
    User {
        email,
        username,
        active: true,
        sign_in_count: 1,
    }
}

fn main() {
    let username = String::from("someusername123");
    let email = String::from("someone@example.com");
    let user1 = build_user(email, username);

    let user2 = User {
        email: String::from("another@example.com"),
        username: String::from("anotherusername567"),
        ..user1
    };
    println!("{} has the email address: {}", user1.username, user1.email);
    println!("{} has the email address: {}", user2.username, user2.email);
}
