use std::io;

pub fn play_game() {
    let mut input_raw = String::new();
    println!("Enter Input:");

    io::stdin().read_line(&mut input_raw)
        .expect("Failed to read line");

    println!("You Entered (raw): {}", input_raw);
    
    let input_split = input_raw.split(",");
    let mut input_list:Vec<i8> = Vec::new(); 
    for s in input_split {
        for i in s.split(" ") {
            match i {
                "A" => input_list.push(14),
                "2" => input_list.push(2),
                "3" => input_list.push(3),
                "4" => input_list.push(4),
                "5" => input_list.push(5),
                "6" => input_list.push(6),
                "7" => input_list.push(7),
                "8" => input_list.push(8),
                "9" => input_list.push(9),
                "T" => input_list.push(10),
                "J" => input_list.push(11),
                "Q" => input_list.push(12),
                "K" => input_list.push(13),
                _ => match i.parse() {
                    Ok(n) => input_list.push(n),
                    Err(e) => (),
                }
            }
        }
    }
    
    input_list.reverse();
    println!("Start Deck (Reversed): {:?}", input_list);

    let mut score:i8 = input_list.pop().unwrap();
    println!("Score: {}", score);

    let mut player_deck = vec![input_list.pop().unwrap(), input_list.pop().unwrap(), input_list.pop().unwrap()];
    println!("Player Deck: {:?}", player_deck);

    let mut turn = "player";
    while score < 100 {
        println!("\nTurn: {}", turn);
        let mut played_card = 0;
        if turn == "player" {
            let mut largest_i = 0;
            let mut largest = player_deck[0];
            println!("Player Deck: {:?}", player_deck);
            for i in 0..3 {
                if player_deck[i] > largest {
                    largest_i = i;
                }
            }
            played_card = player_deck.remove(largest_i);
            if input_list.len() > 0 {
                player_deck.push(input_list.pop().unwrap());
            }
            turn = "dealer";
        } else {
            played_card = input_list.pop().unwrap();
            turn = "player";
        }
        println!("Playing: {}", played_card);
        match played_card {
            14 => {
                if score + 14 > 99 {
                    played_card = 1
                }
            },
            10 => played_card = -10,
            9 => played_card = 0,
            _ => (),
        }
        score += played_card;
        println!("New Score: {}", score);
        println!("Deck: {:?}", input_list);
    }
    println!("\nGame Over");
    println!("{}, {}", score, turn);

    pause_window();
}

fn pause_window() {
    let mut exit = String::new();
    println!("\n\n\nPress enter to exit:");

    io::stdin().read_line(&mut exit)
        .expect("Failed to read line");
}