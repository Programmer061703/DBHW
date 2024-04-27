<!DOCTYPE html>
<html lang="en">
<head>
<meta charset="UTF-8">
<title>Sports Management System</title>
<style>
    body {
        font-family: Arial, sans-serif;
        background-color: #f4f4f9;
        margin: 40px;
        padding: 20px;
    }
    h2 {
        color: #333;
    }
    form {
        margin-top: 20px;
    }
    input[type="submit"] {
        padding: 10px;
        font-size: 16px;
        background-color: #4CAF50;
        color: white;
        border: none;
        border-radius: 5px;
        cursor: pointer;
    }
    input[type="submit"]:hover {
        background-color: #45a049;
    }
</style>
</head>
<body>
<h2>Sports Management System</h2>

<form action="add_game.php" method="post">
    <input type="submit" value="Add a Game">
</form>

<form action="add_player.php" method="post">
    <input type="submit" value="Add a Player">
</form>

<form action="view_players.php" method="post">
    <input type="submit" value="View Players on a Team">
</form>

<form action="view_position_players.php" method="post">
    <input type="submit" value="View Players by Position">
</form>

<form action="view_teams.php" method="post">
    <input type="submit" value="View Teams by Conference">
</form>

<form action="view_team_games.php" method="post">
    <input type="submit" value="View Games by Team">
</form>

<form action="view_results_by_date.php" method="post">
    <input type="submit" value="View Results by Date">
</form>

<form action="add_player_stats.php" method="post">
    <input type="submit" value="Add Player Stats">
</form>

<form action="view_players_game.php" method="post">
    <input type="submit" value="View Players Stats">
</form>

</body>
</html>



