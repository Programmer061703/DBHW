<!DOCTYPE html>
<html lang="en">
<head>
<meta charset="UTF-8">
<title>View Teams by Conference</title>
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
<h2>View Teams by Conference</h2>

<form action="" method="post">
    <label for="conference">Enter Conference:</label>
    <input type="text" id="conference" name="conference" required>
    <input type="submit" name="submit" value="View Teams">
</form>

<?php
if (isset($_POST['submit'])) {
    $conference = escapeshellarg($_POST['conference']); // Secure the conference for the shell command

    // Build the command to execute the external .exe file
    $command = '/path/to/your/executable/view_teams_by_conference.exe ' . $conference;

    echo '<p>Command: ' . htmlspecialchars($command) . '</p>';

    // Sanitize the command to prevent injection attacks
    $command = escapeshellcmd($command);

    // Execute the command and output directly to the page
    system($command);
}
?>

</body>
</html>
