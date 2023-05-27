<?php

$url = 'https://v1.hitokoto.cn/';//

$ch = curl_init();
curl_setopt($ch, CURLOPT_URL, $url);
curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
curl_setopt($ch, CURLOPT_SSL_VERIFYPEER, false);
$result = curl_exec($ch);
curl_close($ch);

$data = json_decode($result, true);

if ($data['length'] < 12 || $data['length'] > 29) {
    sleep(1); // 等待1秒钟
    $result = file_get_contents($url);
    $data = json_decode($result, true);
}

if ($data['from_who'] !== null) {
    $data['from_who'] = '---' . $data['from_who'];
}

$result = json_encode($data, JSON_UNESCAPED_UNICODE);

echo $result;

?>
