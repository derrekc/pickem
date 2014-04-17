<?php

class PickemManager {

	static $GAMES_SPREADSHEET_KEY = '1M58ubV1mzlTaHWgs0YUIn_X3KRpx-M8zqAehG80lNVg';
	static $SCHOOLS_SPREADSHEET_KEY = '1mp_TDlGqvrYZssn_1mU6hLfoekvnWeH-LsYHMRfax6o';
	static $WORKSHEET_URL_PIECE = '%s/feeds/worksheets/%s/public/basic%s';
	static $LIST_URL_PIECE = '%s/feeds/list/%s/%s/public/values';

	static $FEEDURL_PREFIX = 'https://spreadsheets.google.com';
	static $QUERY_STRING = '?alt=json&amp;callback=displayContent';
	
	public static function sampleData() {

		// set timeout length
		$context = stream_context_create(
			array( 
		    'http' => array( 
					'timeout' => 5 
				) 
			) 
		); 
	
		// get data from google in this testing period
		$feed_url = sprintf(PickemManager::WORKSHEET_URL_PIECE, 
			PickemManager::FEEDURL_PREFIX,
			PickemManager::GAMES_SPREADSHEET_KEY,
			PickemManager::QUERY_STRING
			);

		$worksheet_content = json_decode(file_get_contents($feed_url, 0, $context), TRUE);
		$worksheetEntries = $worksheet_content['feed']['entry'];

		$schedKey = PickemManager::gs_scheduleForTitle('acc');
	}

	public static function gs_scheduleForTitle($key) {
		$filter = function($var) {
			$r = preg_match('/listfeed/', $var['rel']);
			return $r == 1;
		};

		$listfeed_urls = array();
		foreach ($worksheetEntries as $ws) {
			$listfeed_urls = array_filter($ws['link'], $filter);
			$list_query_url = str_replace('basic', 'values', sprintf("%s?%s", $listfeed_urls[0]['href'], $queryParams));

			dpm($list_query_url);

			$lists_content = json_decode(file_get_contents($list_query_url, 0, $context), TRUE);
			if ($ws['title']['$t'] == $key) {
				dpm($lists_content);
			}
		}		
	}
}