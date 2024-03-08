<!DOCTYPE html>
<html>
<head>
    <meta http-equiv="refresh" content="5" >
    <link rel="stylesheet" type="text/css" href="style.css" media="screen"/>

	<title> Peaky Blinders </title>

</head>

<body>
    <header><img src="22422.png" width="400" height="400"/></header>
    <h1>Peaky Blinders Parking: Welcome!</h1>
<?php
$servername = "localhost";
$username = "root";
$password = "";
$dbname = "peaky";

// crea  connessione
$conn = new mysqli($servername, $username, $password, $dbname);
// controllo connessione
if ($conn->connect_error) {
    die("Connessione fallita: " . $conn->connect_error);
}

$sql = "SELECT id, location, posti, reading_time FROM sensordata ORDER BY id DESC"; /*select da tabella*/

echo '<table cellspacing="5" cellpadding="5">
      <tr> 
        <th>ID</th> 
        <th>Date $ Time</th> 
        <th>Location</th> 
        <th>Slot</th>       
      </tr>';
 
if ($result = $conn->query($sql)) {
    while ($row = $result->fetch_assoc()) {
        $row_id = $row["id"];
        $row_reading_time = $row["reading_time"];
        $row_location = $row["location"];
        $row_posti = $row["posti"];
         
      
        echo '<tr> 
                <td>' . $row_id . '</td> 
                <td>' . $row_reading_time . '</td> 
                <td>' . $row_location . '</td> 
                <td>' . $row_posti . '</td> 
                
              </tr>';
    }
    $result->free();
}

$conn->close();
?> 
</table>

</body>
</html>

	</body>
</html>