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
</style>
</head>
<body>
<h2>Add a Player to the Database</h2>

<form action="add_player.php" method="post">
    <label for="teamId">Team ID:</label>
    <input type="number" id="teamId" name="teamId" required><br>

    <label for="name">Player Name:</label>
    <input type="text" id="name" name="name" required><br>

    <label for="position">Position:</label>
    <input type="text" id="position" name="position" required><br>

    <input type="submit" name="submit" value="Add Player">
</form>

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
