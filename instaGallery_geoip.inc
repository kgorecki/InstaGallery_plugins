<?php

// Writes information about visitors to file.

$entrylog_file = 'entries.jsons';
$geoip_api_url = 'http://freegeoip.net/json/';
$client_ip = $_SERVER['REMOTE_ADDR'];

$client_details = file_get_contents($geoip_api_url . $client_ip);

if (!empty($client_details))
	file_put_contents($entrylog_file, $client_details . PHP_EOL , FILE_APPEND | LOCK_EX);
else
	file_put_contents($entrylog_file, $client_ip . PHP_EOL , FILE_APPEND | LOCK_EX);
