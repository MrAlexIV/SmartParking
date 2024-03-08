<?php
$servername = "localhost";
$username = "root";
$password = "";
$dbname = "peaky";


$api_key_value = "tPmAT5Ab3j7F9";

$api_key= $location = $posti = "";

if ($_SERVER["REQUEST_METHOD"] == "POST") { // verifica se la richiesta ricevuta è un POST
    $api_key = test_input($_POST["api_key"]); // acquisisce key
    if($api_key == $api_key_value) { // se le key sono uguali,acquisisce dati
        $location = test_input($_POST["location"]);
        $posti = test_input($_POST["posti"]);
        
        
        // creo connessione
        $conn = new mysqli($servername, $username, $password, $dbname);
        // controllo connessione
        if ($conn->connect_error) {
            die("connessione fallita: " . $conn->connect_error);
        } 
        
        $sql = "INSERT INTO SensorData (location, posti)
        VALUES ('" . $location . "', '" . $posti . "')";
        
        if ($conn->query($sql) === TRUE) {
            echo "New record creato";
        } 
        else {
            echo "Error: " . $sql . "<br>" . $conn->error;
        }
    
        $conn->close();
    }
    else {
        echo "Wrong API Key.";
    }

}
else {
    echo "No data.";
}
// controllo stringhe
function test_input($data) {
    $data = trim($data); // rimuovo caratteri strani
    $data = stripslashes($data); // rimuovo backslashes 
    $data = htmlspecialchars($data); // converto caratteri predefiniti in entità hmtl
    return $data;
}