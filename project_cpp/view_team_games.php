<!DOCTYPE html>
<html lang="en">
<head>
<meta charset="UTF-8">
<title>View Games by Team</title>
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
    input[type="text"], input[type="submit"] {
        padding: 8px;
        margin-top: 10px;
        border-radius: 4px;
        border: 1px solid #ccc;
    }
    input[type="submit"] {
        background-color: #4CAF50;
        color: white;
        cursor: pointer;
    }
    input[type="submit"]:hover {
        background-color: #45a049;
    }
    table {
        width: 100%;
        margin-top: 20px;
        border-collapse: collapse;
    }
    th, td {
        padding: 8px;
        text-align: left;
        border-bottom: 1px solid #ddd;
    }
</style>
</head>
<body>
<h2>View Games by Team</h2>

<form action="" method="post">
    <label for="teamName">Enter Team Name:</label>
    <input type="text" id="teamName" name="teamName" required>
    <input type="submit" name="submit" value="View Games">
</form>

<?php
if (isset($_POST['submit'])) {
    $teamName = escapeshellarg($_POST['teamName']); // Secure the team name for the shell command

    // Build the command to execute the external .exe file
    $command = '/path/to/your/executable/view_games_by_team.exe ' . $teamName;

    // Sanitize the command to prevent injection attacks
    $command = escapeshellcmd($command);

    // Execute the command and output directly to the page
    system($command);
}
?>

</body>
</html>
