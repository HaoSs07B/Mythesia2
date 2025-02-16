quest pda_perf_quest begin
	state start begin
		function GetSkillList()
			local skill_list = special.active_skill_list[pc.get_job()+1][pc.get_skill_group()]
			local vnum_list = {}
			local name_list = {}
			for i = 1,table.getn(skill_list) do
				local skill_vnum = skill_list[i]
				local skill_level = pc.get_skill_level(skill_vnum)
				if skill_level >= 30 and skill_level < 40 then
					table.insert(vnum_list, skill_list[i])
					table.insert(name_list, locale.GM_SKILL_NAME_DICT[skill_vnum])
				end
			end
			return vnum_list, name_list
		end

		when 50525.use begin
			if pc.get_map_index() >= 10000 then
				syschat(gameforge[pc.get_language()].common.cannot_use_dung)
				return
			end
			
			if not pc.can_warp() then
				syschat(gameforge[pc.get_language()].reset_scroll._35)
				return
			end
			
			say_title(string.format("%s:", item_name(50525)))
			say("")
			local lang = pc.get_language()
			if pc.get_skill_group() == 0 then
				say(gameforge[lang].pda_perf_quest._1)
				return
			end
			
			local vnum_list, name_list = pda_perf_quest.GetSkillList(1)
			say(gameforge[lang].pda_perf_quest._2)
			say(gameforge[lang].pda_perf_quest._3)
			say(gameforge[lang].pda_perf_quest._4)
			if table.getn(vnum_list) == 0 then
				say_reward(gameforge[lang].pda_perf_quest._5)
				return
			end
			
			select(gameforge[lang].common.wait)
			say_title(string.format("%s:", item_name(50525)))
			say("")
			say(gameforge[lang].pda_perf_quest._5)
			table.insert(name_list, gameforge[lang].pda_perf_quest._7) 
			local s = select_table(name_list)
			if s == table.getn(name_list) then
				return
			end
			
			local skill_name = name_list[s]
			local skill_vnum = vnum_list[s]
			say_title(string.format("%s:", item_name(50525)))
			say("")
			say(string.format(gameforge[lang].pda_perf_quest._8, skill_name))
			say(gameforge[lang].pda_perf_quest._9)
			local a = select(gameforge[lang].common.yes, gameforge[lang].common.no)
			if a == 2 then
				return
			end
			
			say_title(string.format("%s:", item_name(50525)))
			say("")
			say(string.format(gameforge[lang].pda_perf_quest._10, skill_name))
			pc.set_skill_level (skill_vnum, 40)
			pc.remove_item(item.get_vnum(), 1)
		end
	end
end

