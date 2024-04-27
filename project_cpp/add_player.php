<!DOCTYPE html>
<html lang="en">
<head>
<meta charset="UTF-8">
<title>Add Player</title>
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
    input[type="text"], input[type="number"] {
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
<h2>Add a Player to the Database</h2>

<form action="add_player.php" method="post">

    <label for="teamId">Team ID:</label>
    <input type="number" id="teamId" name="teamId" required><br>

    <label for="name">Player Name:</label>
    <input type="text" id="name" name="name" required><br>

    <label for="position">Player Position:</label>
    <select id="position" name="position" required>
        <option value="Quarterback">Quarterback</option>
        <option value="Running Back">Running Back</option>
        <option value="Wide Receiver">Wide Receiver</option>
        <option value="Tight End">Tight End</option>
        <option value="Offensive Lineman">Offensive Lineman</option>
        <option value="Defensive Tackle">Defensive Tackle</option>
        <option value="Defensive End">Defensive End</option>
        <option value="Linebacker">Linebacker</option>
        <option value="Cornerback">Cornerback</option>
        <option value="Safety">Safety</option>
        <option value="Kicker">Kicker</option>
        <option value="Punter">Punter</option>
    </select><br>

    <input type="submit" name="submit" value="Add Player">
</form>
<div class="button-container">
    <a href="main.php" class="button">Return to Menu</a>
</div>

<?php
if (isset($_POST['submit'])) {
    // Escape the input to use as command line arguments
    $teamId = escapeshellarg($_POST['teamId']);
    $name = escapeshellarg($_POST['name']);
    $position = escapeshellarg($_POST['position']);

    // Build the command
    $command = '/home/brw020/public_html/project_cpp/add_player.exe ' . $teamId . ' ' . $name . ' ' . $position;

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
