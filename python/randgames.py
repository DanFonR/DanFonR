from requests import get
from random import sample
from time import time

WISHLIST_URI = (
    "https://api.steampowered.com/IWishlistService/GetWishlist" +
    "/v1/?steamid=76561198089243743"
)
GAMES_URI = lambda x: (
    f"https://store.steampowered.com/api/appdetails?appids={x}" +
    "&locale=pt_br"
)


init_time = time()
try:
    wishlist = get(WISHLIST_URI).json()
    wishlist = wishlist.get("response").get("items")
except:
    print("smth went wrong")
    exit(1)

wishlist_time = time()

print(f"got wishlist in {wishlist_time - init_time: .4f}s")

games = []

loop_init_time = time()

for item in wishlist:
    try:
        game = get(GAMES_URI(item["appid"])).json()
        game = game.get(f"{item["appid"]}")

        if not game["success"]: continue

        game = game.get("data")
    except:
        print(f"error on game id {item["appid"]}")
        continue

    try:
        if game["is_free"]:
            games.append((game["name"], 0))
            continue

        prices = game.get("price_overview")

        if not prices:
            games.append((game["name"], -1.00))
            continue

        if prices["discount_percent"] != 0:
            games.append((game["name"], prices["final"] / 100))
    except:
        print(game)
        continue

loop_end_time = time()

print(f"list processed in {loop_end_time - loop_init_time: .4f}s")


print(games)
