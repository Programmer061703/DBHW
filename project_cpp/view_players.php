<!DOCTYPE html>
<html lang="en">
<head>
<meta charset="UTF-8">
<title>View Players on a Team</title>
<style>
    body {
        font-family: Arial, sans-serif;
        background-color: #f4f4f9;
        margin: 20px;
        padding: 20px;
    }
    select, input[type="submit"] {
        padding: 10px;
        margin-top: 10px;
        border-radius: 4px;
        border: 1px solid #ccc;
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
<h2>View Players on a Team</h2>

<form action="view_players_on_team.php" method="post">
    <label for="teamId">Select Team ID:</label>
    <input type="number" id="teamId" name="teamId" required>
    <input type="submit" name="submit" value="View Players">
</form>




</body>
</html>