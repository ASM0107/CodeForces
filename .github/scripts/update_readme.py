import sys
import os
import re
import json
import urllib.request

def fetch_cf_user(handle):
    url = f"https://codeforces.com/api/user.info?handles={handle}"
    try:
        with urllib.request.urlopen(url, timeout=10) as response:
            data = json.loads(response.read().decode())
            if data.get("status") == "OK":
                return data["result"][0]
    except Exception as e:
        print(f"Error fetching Codeforces API: {e}", file=sys.stderr)
    return None

def main():
    handle = "asmofficial172006"
    cf_data = fetch_cf_user(handle)
    
    # Defaults in case of API failure
    rating = None
    max_rating = None
    rank = None
    
    if cf_data:
        rating = cf_data.get("rating")
        max_rating = cf_data.get("maxRating")
        rank = cf_data.get("rank")
        print(f"Fetched from CF API: Rating={rating}, MaxRating={max_rating}, Rank={rank}")
    else:
        print("Using fallback/existing values for Codeforces stats due to API failure.")

    # Count actual files in the repository
    problems_count = 0
    contests_count = 0
    contests_dir = "contests"
    
    if os.path.exists(contests_dir):
        # Count directories inside contests/
        contests_count = len([d for d in os.listdir(contests_dir) if os.path.isdir(os.path.join(contests_dir, d))])
        # Count all .cpp files recursively in contests/
        for root, _, files in os.walk(contests_dir):
            for file in files:
                if file.endswith(".cpp"):
                    problems_count += 1
                    
    print(f"Calculated repo stats: Contests={contests_count}, Problems={problems_count}")

    # Read README.md
    readme_path = "README.md"
    if not os.path.exists(readme_path):
        print(f"Error: {readme_path} not found.", file=sys.stderr)
        sys.exit(1)
        
    with open(readme_path, "r", encoding="utf-8") as f:
        content = f.read()

    # Update problems count badge
    # Format: https://img.shields.io/badge/Problems-20-2d333b
    content = re.sub(
        r'https://img\.shields\.io/badge/Problems-\d+-2d333b',
        f'https://img.shields.io/badge/Problems-{problems_count}-2d333b',
        content
    )

    # Update contests count badge
    # Format: https://img.shields.io/badge/Contests-4-2d333b
    content = re.sub(
        r'https://img\.shields\.io/badge/Contests-\d+-2d333b',
        f'https://img.shields.io/badge/Contests-{contests_count}-2d333b',
        content
    )

    # Update CF rating badge & stats if API call was successful
    if rating and rank:
        rank_display = " ".join([w.capitalize() for w in rank.split()])
        rank_badge_val = f"{rank_display}_%7C_{rating}".replace(" ", "%20")
        
        # Determine color based on rank
        rank_colors = {
            "newbie": "808080",
            "pupil": "008000",
            "specialist": "03a89e",
            "expert": "1a8cff",
            "candidate master": "aa00aa",
            "master": "ff8c00",
            "international master": "ff8c00",
            "grandmaster": "ff0000",
            "international grandmaster": "ff0000",
            "legendary grandmaster": "ff0000"
        }
        color = rank_colors.get(rank.lower(), "1a8cff")
        
        # Replace Codeforces badge URL
        # Format: https://img.shields.io/badge/Codeforces-Expert_%7C_1658-1a8cff
        badge_pattern = r'https://img\.shields\.io/badge/Codeforces-[a-zA-Z0-9%_\\|\\s\\-~]+-[a-fA-F0-9]+'
        content = re.sub(
            badge_pattern,
            f'https://img.shields.io/badge/Codeforces-{rank_badge_val}-{color}',
            content
        )
        
        # Replace tagline: `asmofficial172006` · Expert · 0 → 1658 in 4 rated contests
        tagline_pattern = r'`asmofficial172006` · [A-Za-z\s]+ · \d+ → \d+ in \d+ rated contests'
        tagline_replacement = f'`asmofficial172006` · {rank_display} · 0 → {rating} in {contests_count} rated contests'
        content = re.sub(tagline_pattern, tagline_replacement, content)
        
        # Write stats to stats.json
        stats = {
            "problems_solved": problems_count,
            "contests": contests_count,
            "rating": rating,
            "max_rating": max_rating,
            "rank": rank,
            "last_updated": urllib.request.urlopen("https://codeforces.com/api/user.info?handles=asmofficial172006").info().get("Date", "")
        }
        with open("stats.json", "w", encoding="utf-8") as sf:
            json.dump(stats, sf, indent=2)
            
    with open(readme_path, "w", encoding="utf-8") as f:
        f.write(content)
        
    print("README.md and stats.json successfully updated.")

if __name__ == "__main__":
    main()
