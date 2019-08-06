function [score, winner] = main(input)
    dealer_deck = split(input, ',');
    [score, dealer_deck] = pop(dealer_deck);
    score = str2double(score);
    player_deck = {};
    for i = 2:4
        [value, dealer_deck] = pop(dealer_deck); 
        player_deck(i-1) = value;
    end
    player_turn = true;

    while score <= 99
        if player_turn
            [value, player_deck] = get_max(player_deck);
            [new_value, dealer_deck] = pop(dealer_deck);   
            player_deck(3) = new_value;
        else
            [value, dealer_deck] = pop(dealer_deck);       
        end
        score = score + point_change(score, value);
        player_turn = ~player_turn;
    end
    if player_turn
        winner = "player";
    else
        winner = "dealer";
    end
end

function [value, array] = pop(array)
    assert(~isempty(array));
    value = array(1);
    array = array(2:end);
end

function [value, deck] = get_max(deck)
    value = 0;
    largest = 0;
    largest_i = 0;
    for i = 1:length(deck)
        if get_value(deck(i)) > largest
            largest = get_value(deck(i));
            value = deck(i);
            largest_i = i;
        end
    end
    deck(largest_i) = [];
end

function value = get_value(chr)
    chr = char(strtrim(chr));
    switch chr
        case 'T'
            value = 10;
        case 'J'
            value = 11;
        case 'Q'
            value = 12;
        case 'K'
            value = 13;
        case 'A'
            value = 14;
        otherwise
            value = str2double(chr);
    end
end

function value = point_change(score, chr)
chr = char(strtrim(chr));
    switch chr
        case '9'
            value = 0;
        case 'T'
            value = -10;
        case 'J'
            value = 11;
        case 'Q'
            value = 12;
        case 'K'
            value = 13;
        case 'A'
            if score + 14 > 99
                value = 1;
            else
                value = 14;
            end
        otherwise
            value = str2double(chr);
    end
end

