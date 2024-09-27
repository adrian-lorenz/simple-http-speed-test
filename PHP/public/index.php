<?php
    header('Content-Type: application/json');
    $response = ['message' => 'Hello, this is a test response'];
    echo json_encode($response);
    exit;

?>
