<!DOCTYPE html>
<html lang="en">
<head>
<meta charset="UTF-8">
<title>View Players by Position</title>
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
    .button-container {
        
        margin-top: 10px; 
        text-align: center; 
    }
</style>
</head>
<body>
<h2>View Players by Position</h2>

<form action="" method="post">
    <label for="position">Enter Position:</label>
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
    <input type="submit" name="submit" value="View Players">
</form>
<div class="button-container">
    <a href="main.php" class="button">Return to Menu</a>
</div>

<?php
if (isset($_POST['submit'])) {
    $position = escapeshellarg($_POST['position']); // Secure the position for the shell command

    // Build the command to execute the external .exe file
    $command = '/home/brw020/public_html/project_cpp/view_position_players.exe ' . $position;

    echo '<p>Command: ' . htmlspecialchars($command) . '</p>';

    // Sanitize the command to prevent injection attacks
    $command = escapeshellcmd($command);

    // Execute the command and output directly to the page
    system($command);  
}
?>

</body>
</html>
