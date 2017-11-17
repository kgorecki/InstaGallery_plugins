<?php
//TODO:
// remove entries from CSV which are not covered by files
// add possibility to format title / add text
// create RSS feed

$titles_csv = 'titles.csv';

function readFilenamesFromCSV($titles_csv) {
  $result = array();
  if (($handle = fopen($titles_csv, "r")) !== FALSE) {
    while (($data = fgetcsv($handle, 1000, ",")) !== FALSE) {
      array_push($result, $data[0]);
    }
    fclose($handle);
  }
  return $result;
}

function writeFilenamesToCSV($titles_csv, $filelist) {
  $csvfile = fopen($titles_csv,'a');
  $finfo = finfo_open(FILEINFO_MIME_TYPE);
  foreach ($filelist as $mediafile) { 
    $mime = finfo_file($finfo, $mediafile);

    if (strpos($mime, 'image') === 0) {
      $exif = exif_read_data($mediafile, 'ANY_TAG');
      if (is_array($exif) === true) {
        $timestamp = @$exif['DateTimeOriginal'];
        $entry = array($mediafile, ($timestamp == '' ? $mediafile : $timestamp));
      } else
        $entry = array($mediafile, $mediafile);
      fputcsv($csvfile, $entry);
    }
  }
  fclose($csvfile);
}

$media = getMedia($path);
$filesInCSV = readFilenamesFromCSV($titles_csv);
$missingFiles = array();

foreach ($media as $mediafile => $title) {
  if (!in_array($mediafile, $filesInCSV)) {
    array_push($missingFiles, $mediafile);
  }
}

if (count($missingFiles))
  writeFilenamesToCSV($titles_csv, $missingFiles);
