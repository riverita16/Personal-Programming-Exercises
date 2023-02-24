# Import random functionality
from random import randint


# Function to get card from randomly generated number
def get_card(value):
    if value == 1:
        card = 'ACE'
    elif value in range(2,11):
        card = value
    elif value == 11:
        card = 'JACK'
    elif value == 12:
        card = 'QUEEN'
    else:
        card = 'KING'
    
    return card


# Function that prints menu and returns user selection
def menu_options():
    print('1. Get another card')
    print('2. Hold hand')
    print('3. Print statistics')
    print('4. Exit\n')
    
    # Deals with non-integer input for option choice prompt
    try:
        selection = int(input('Choose an option: '))
    except Exception:
        return 0
    
    return selection


# Function that deals with user's menu choice
def selection_functionality(selection, player_hand, stats, num1 = None):
    # Selection funcionality
    if selection == 1:
        # Deals player another card
        new_value = num1
        new_card = get_card(new_value)
        print(f'\nYour card is a {new_card}!')

        # Adds new card's value to the player's hand
        if new_value > 10:
            player_hand += 10
        else:
            player_hand += new_value

        # Prints player's hand
        print(f'Your hand is: {player_hand}\n')

        # Checks for blackjack or hand over 21
        if player_hand == 21:
            print('BLACKJACK! You win!\n')
            return 1
        elif player_hand > 21:
            print('You exceeded 21! You lose.\n')
            return 2
        
        return str(player_hand)
    
    elif selection == 2:
        # Ramndomly generates dealer's hand
        dealer_hand = num1

        # Prints dealer and player hands
        print(f'\nDealer\'s hand: {dealer_hand}')
        print(f'Your hand is: {player_hand}\n')

        # Compares dealer and player hands to determine who wins
        if dealer_hand > 21 or dealer_hand < player_hand:
            print('You win!\n')
            return 1
        elif dealer_hand == player_hand:
            print('It\'s a tie! No one wins!\n')
            return 0
        else:
            print('Dealer wins!\n')
            return 2

    elif selection == 3:
        # Prints game stats
        print_stats(stats)
        return str(player_hand)
    else:
        # Ends game; exits program
        exit()


# Function that prints stats for menu choice 4
def print_stats(stats):
    # Stores stats array values in corresponsing variables
    games = stats[0] - 1   # Accounts for current game
    player_wins = stats[1]
    dealer_wins = stats[2]
    ties = stats[3]

    # Calculates percentage of player wins
    percentage = (player_wins / games) * 100

    # Prints all stats
    print(f'\nNumber of Player wins: {player_wins}')
    print(f'Number of Dealer wins: {dealer_wins}')
    print(f'Number of tie games: {ties}')
    print(f'Total # of games played is: {games}')
    print(f'Percentage of Player wins: {percentage:.01f}%\n')


if __name__ == '__main__':    
    # Game statistics variables
    game_count = 1
    player_wins = 0
    dealer_wins = 0
    ties = 0

    # Generates new game until user exits
    while True:
        # Stores statistics for the game
        stats = [game_count, player_wins, dealer_wins, ties]

        # Prints game start and deals starting hand
        print(f'START GAME #{game_count}\n')
        first_hand = randint(1,13)
        card = get_card(first_hand)
        print(f'Your card is a {card}!')

        # Deals with jack, queen, and king value of 10 and assigns card value to player hand
        if first_hand > 10:
            player_hand = 10
        else:
            player_hand = first_hand

        # Prints player's hand
        print(f'Your hand is: {player_hand}\n')

        # Loop for menu screen until win, lose, tie, or exit
        while True:
            # Prints menu on screen and gets user selection
            selection = menu_options()

            # Checks for valid choice or prompts the user again
            while selection not in range(1, 5):
                print('\nInvalid input!')
                print('Please enter an integer value between 1 and 4.\n')
                selection = menu_options()
            
            # Continues game based on user selection
            num1 = randint(1,13)
            if selection == 1:
                result = selection_functionality(selection, player_hand, stats, num1)
            elif selection == 2:
                result = selection_functionality(selection, player_hand, stats, num1)
            else:
                result = selection_functionality(selection, player_hand, stats)
            
            if type(result) == int:
                if result in range(0,3):
                    # Updates variables based on the result of the game
                    if result == 1:
                        player_wins += 1
                    elif result == 2:
                        dealer_wins += 1
                    else:
                        ties += 1
                    
                    # Increment game count
                    game_count += 1

                    break
            
            # Stores current player's hand for the loop
            player_hand = int(result)


