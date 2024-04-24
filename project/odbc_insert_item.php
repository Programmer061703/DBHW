<html>
<body>
<h3>Enter information about an item to add to the database:</h3>

<div>
    <b>Suppliers:</b>
    <table>
    <thead>
    <tr>
        <th>ID</th>
        <th>Name</th>
    </tr>
    </thead>
    <tbody>
    <tr>
        <td>1</td>
        <td>Coco Fresh Tea &amp; Juice</td>
    </tr>
    <tr>
        <td>3</td>
        <td>Sharetea</td>
    </tr>
    <tr>
        <td>4</td>
        <td>Boba Guys</td>
    </tr>
    <tr>
        <td>8</td>
        <td>Kung Fu Tea</td>
    </tr>
    <tr>
        <td>15</td>
        <td>Fat Straws</td>
    </tr>
    </tbody>
    </table>
</div>

<form action="odbc_insert_item.php" method="post">
    Name: <input type="text" name="name"><br>
    Supplier id: <input type="text" name="supplier_id"><br>
    Quantity: <input type="text" name="quantity"><br>
    Unit Price: <input type="text" name="unit_price"><br>
    <input name="submit" type="submit" >
</form>
<br><br>

</body>
</html>

<?php
if (isset($_POST['submit'])) 
{
    // replace ' ' with '\ ' in the strings so they are treated as single command line args
    $name = escapeshellarg($_POST[name]);
    $supplier_id = escapeshellarg($_POST[supplier_id]);
    $quantity = escapeshellarg($_POST[quantity]);
    $unit_price = escapeshellarg($_POST[unit_price]);

    $command = '/home/brw020/public_html/project_cpp/odbc_insert_item.exe ' . $name . ' ' . $supplier_id . ' ' . $quantity. ' ' . $unit_price;

    echo '<p>' . 'command: ' . $command . '<p>';
    // remove dangerous characters from command to protect web server
    $command = escapeshellcmd($command);
 
    // run odbc_insert_item.exe
    system($command);           
}
?>


