<!DOCTYPE html>
<html lang="en">
<head>
<meta charset="UTF-8">
<title>Add Game</title>
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
    input[type="text"], input[type="date"] {
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
    input[type="submit"]:hover, .button:hover {
        background-color: #45a049;
    }
    .button-container {
        
        margin-top: 10px; 
        text-align: center; 
    }
</style>
</head>
<body>
<h2>Add a Game to the Database</h2>

<form action="add_game.php" method="post">

    <label for="teamId1">Team ID 1:</label>
    <input type="text" id="teamId1" name="teamId1"><br>

    <label for="teamId2">Team ID 2:</label>
    <input type="text" id="teamId2" name="teamId2"><br>

    <label for="score1">Score 1:</label>
    <input type="text" id="score1" name="score1"><br>

    <label for="score2">Score 2:</label>
    <input type="text" id="score2" name="score2"><br>

    <label for="date">Date (YYYY-MM-DD):</label>
    <input type="date" id="date" name="date"><br>

    <input type="submit" name="submit" value="Add Game">
</form>

<div class="button-container">
    <a href="main.php" class="button">Return to Menu</a>
</div>


<?php
if (isset($_POST['submit'])) {
    // Escape the input to use as command line arguments
    $teamId1 = escapeshellarg($_POST[teamId1]);
    $teamId2 = escapeshellarg($_POST[teamId2]);
    $score1 = escapeshellarg($_POST[score1]);
    $score2 = escapeshellarg($_POST[score2]);
    $date = escapeshellarg($_POST[date]);

    // Build the command
    $command = '/home/brw020/public_html/project_cpp/add_game.exe ' . $teamId1 . ' ' . $teamId2 . ' ' . $score1 . ' ' . $score2 . ' ' . $date;

    // Display the command for debugging
    echo '<p>Command: ' . $command . '</p>';

    // Sanitize the command to prevent injection attacks
    $command = escapeshellcmd($command);

    // Execute the command
    system($command);           
}
?>

</body>
</html>
