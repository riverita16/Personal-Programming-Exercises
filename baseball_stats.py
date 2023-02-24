# Implementation requires rapidapi account
import requests
import json

url = "https://odds.p.rapidapi.com/v4/sports/americanfootball_nfl/scores"

# Inseet API Key here
headers = {
	"X-RapidAPI-Key": "3fd7321ca3mshb08add3fa54a969p1a096ejsndb10b4a8ec0e",
	"X-RapidAPI-Host": "odds.p.rapidapi.com"
}


if __name__ == "__main__":
    days = 0
    while not days > 0:
        days = int(input("From how many days do you want MLB scores? (1-3): ")) # Prompt day range for scores 

        if days == 0:
            print("Bye!") # End program if none
            exit()

    num_teams = 0
    while not num_teams > 0:
        num_teams = int(input("From how many teams do you want MLB score data? ")) # Prompt for how many teams' data

        if num_teams == 0:
            print("Bye") # End program if none
            exit()

    teams = []
    for i in range(num_teams):
        teams.append(input(f"Enter team {i+1} full name: ")) # Prompt for team name

    querystring = {"sport":"baseball_mlb", "daysFrom":days}

    # Handle response
    try:
        response = json.loads(requests.request("GET", url, headers=headers, params=querystring))
    except:
        print("\nNo stats available today :c")
        exit()

    length = len(response)

    # Check for stats matching requested teams and print matches
    count = 0
    for i in range(length):
        home_team = response[i]["home_team"]
        away_team = response[i]["away_team"]

        if home_team in teams or away_team in teams:
            date = response[i]["commencement_time"][:10]
            print(f"\nGame: {home_team} v {away_team} {date}")
            scores = response[i]["scores"]
            home_score = scores[0]["scores"]
            away_score = scores[1]["scores"]
            print(f"{home_score} - {away_score}")
            count += 1

    if count == 0:
        print("No stats for those teams todat :c")