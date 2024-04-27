<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>View Player Games</title>
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
        input[type="number"], input[type="submit"] {
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
<h2>View Player Games and Statistics</h2>

<form action="view_players_game.php" method="post">
    <label for="playerId">Player ID:</label>
    <input type="number" id="playerId" name="playerId" required>
    <input type="submit" name="submit" value="View Games">
</form>
<div class="button-container">
    <a href="main.php" class="button">Return to Menu</a>
</div>

<?php
if (isset($_POST['submit'])) {
    $playerId = escapeshellarg($_POST['playerId']); // Secure the team name for the shell command

    // Build the command to execute the external .exe file
    $command = '/home/brw020/public_html/project_cpp/view_players_game.exe ' . $playerId;

    // Sanitize the command to prevent injection attacks
    $command = escapeshellcmd($command);
    echo '<p>Command: ' . $command . '</p>';

    // Execute the command and output directly to the page
    system($command);
}
?>

</body>
</html>
