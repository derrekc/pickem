<?php

class Game extends Entity {
	
	public function __construct($values = array()) {
		parent::__construct($values, 'game');

		// load the host school data
		$host_team = entity_load('team', FALSE, array('name' => $this->host_school_name));
		$this->host_team = reset($host_team);

		// load the visiting school data
		$visiting_team = entity_load('team', FALSE, array('name' => $this->visiting_school_name));
		$this->visiting_team = reset($visiting_team);
	}
	
	public function completed() {
		return in_array($this->completed, array('Y', 'y'));
	}

	public function title() {
		return $this->displayTitle();
	}

	public function getDisplayTitle() {
		return $this->displayTitle();
	}
	
	public function displayTitle() {
		if (!empty($this->title)) {
			return $this->title;
		}
		return sprintf('%s %s %s',
			$this->visiting_team->displaytitle,
			$this->neutral == 'Y' ? 'vs.' : 'at',
			$this->host_team->displaytitle
			);
	}

	public function displayTitleMobile() {
		if (!empty($this->title)) {
			return $this->title;
		}
		return sprintf('%s %s<br />%s',
			$this->visiting_school,
			$this->neutral == 'Y' ? 'vs.' : 'at',
			$this->host_school
			);
	}
		
	public function vs_at_label() {
		return $this->neutral == 'Y' ? 'vs.' : 'at';
	}
	
	public function eventDate($type='medium') {
		return $this->gameDate($type);
	}
	
	public function gameDate($type='medium') {
		return format_date($this->game_date, $type);
	}

	public function opponentsForSelectElement() {
		$options = array();
		if (!empty($this->visiting_school_name)) {
			$options[$this->visiting_school_name] = $this->visiting_school;
		}
		if (!empty($this->host_school_name)) {
			$options[$this->host_school_name] = $this->host_school;
		}
		return $options;
	}
	
	public function opponents() {
		$opponents = array();
		
		/**
		 * TODO include rank of school
		 */
		$o = new stdClass();
		$o->name = $this->visiting_school_name;
		$o->displaytitle = $this->visiting_school;
		$opponents['visitor'] = $o;
		
		$o = new stdClass();
		$o->name = $this->host_school_name;
		$o->displaytitle = $this->host_school;
		$opponents['host'] = $o;
		
		return $opponents;
	}
}

class GameUIController extends EntityDefaultUIController {
	
}

class GameAPIController extends EntityAPIController {
	
	public function load($ids = array(), $conditions = array()) {
		return parent::load($ids, $conditions);
	}	
}
