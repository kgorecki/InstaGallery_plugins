<?php
$titles_csv = 'titles.csv';
$media = getMedia($path);

$csvfile = fopen($titles_csv,'w');
foreach ($media as $mediafile => $title) {
  $finfo = finfo_open(FILEINFO_MIME_TYPE);
  $mime = finfo_file($finfo, $mediafile);

  if (strpos($mime, 'image') === 0) {
    $exif = exif_read_data($mediafile, 'ANY_TAG');
    if (is_array($exif) === true) {
      $timestamp = $exif['DateTimeOriginal'];
      $entry = array($mediafile, ($timestamp == '' ? $mediafile : $timestamp));
      fputcsv($csvfile, $entry);
    }
  }
}
fclose($csvfile);
