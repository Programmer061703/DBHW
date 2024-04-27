<!DOCTYPE html>
<html lang="en">
<head>
<meta charset="UTF-8">
<title>Add Player Statistics</title>
<style>
    body {
        font-family: Arial, sans-serif;
        background-color: #f4f4f9;
        margin: 20px;
        padding: 20px;
    }
    form {
        margin-top: 20px;
    }
    label {
        margin-right: 10px;
    }
    input[type="text"], input[type="number"], input[type="submit"] {
        margin-bottom: 10px;
        padding: 8px;
        border-radius: 4px;
        border: 1px solid #ccc;
    }
    input[type="submit"] {
        padding: 10px 20px;
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
    .button-container {
        
        margin-top: 10px; 
        text-align: center; 
    }
</style>
</head>
<body>
<h2>Add Player Statistics</h2>

<form action="add_player_stats.php" method="post">
    
    <label for="playerId">Player ID:</label>
    <input type="number" id="playerId" name="playerId" required><br>

    <label for="gameId">Game ID:</label>
    <input type="number" id="gameId" name="gameId" required><br>

    <label for="touchdowns">Touchdowns:</label>
    <input type="number" id="touchdowns" name="touchdowns" required><br>

    <label for="passingYards">Passing Yards:</label>
    <input type="number" id="passingYards" name="passingYards" required><br>

    <label for="rushingYards">Rushing Yards:</label>
    <input type="number" id="rushingYards" name="rushingYards" required><br>

    <label for="receptions">Receptions:</label>
    <input type="number" id="receptions" name="receptions" required><br>

    <label for="tackles">Tackles:</label>
    <input type="number" id="tackles" name="tackles" required><br>

    <label for="interceptions">Interceptions:</label>
    <input type="number" id="interceptions" name="interceptions" required><br>

    <input type="submit" name="submit" value="Add Player Stats">
</form>
<div class="button-container">
    <a href="main.php" class="button">Return to Menu</a>
</div>

<?php
if (isset($_POST['submit'])) {
    // Escape the input to use as command line arguments
    $playerId = escapeshellarg($_POST['playerId']);
    $gameId = escapeshellarg($_POST['gameId']);
    $touchdowns = escapeshellarg($_POST['touchdowns']);
    $passingYards = escapeshellarg($_POST['passingYards']);
    $rushingYards = escapeshellarg($_POST['rushingYards']);
    $receptions = escapeshellarg($_POST['receptions']);
    $tackles = escapeshellarg($_POST['tackles']);
    $interceptions = escapeshellarg($_POST['interceptions']);

    // Build the command
    $command = '/home/brw020/public_html/project_cpp/add_player_stats.exe '  . $playerId . ' ' . $gameId . ' ' . $touchdowns . ' ' . $passingYards . ' ' . $rushingYards . ' ' . $receptions . ' ' . $tackles . ' ' . $interceptions;

    // Display the command for debugging (optional)
    echo '<p>Command: ' . htmlspecialchars($command) . '</p>';

    // Sanitize the command to prevent injection attacks
    $command = escapeshellcmd($command);

    // Execute the command
    system($command);           
}
?>

</body>
</html>
