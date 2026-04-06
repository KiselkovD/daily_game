.PHONY: build clean clean-data run

# Папки
BUILD_DIR = build
DATA_DIR = data

# Собрать проект
build:
	mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR) && cmake .. && cmake --build .

# Очистить сборку (только билд)
clean:
	rm -rf $(BUILD_DIR)

# Очистить сохранённые данные
clean-data:
	rm -rf $(DATA_DIR)

# Полная очистка (билд + данные)
clean-all: clean clean-data

# Создать папку для данных (если нет)
$(DATA_DIR):
	mkdir -p $(DATA_DIR)

# Запустить собранную программу (с автоматическим созданием data/)
run: $(DATA_DIR)
	if [ -f $(BUILD_DIR)/daily_game ]; then \
		$(BUILD_DIR)/daily_game; \
	else \
		echo "Binary $(BUILD_DIR)/daily_game not found, run 'make build' first."; \
	fi

# Экспорт проекта в txt.txt (как было)
export:
	@echo "Exporting project files to txt.txt..."
	@tree -fi 2>/dev/null | while read file; do \
		echo ""; \
		echo "// $$file"; \
		if [ -f "$$file" ]; then \
			if [ $$(stat -c%s "$$file") -gt 1048576 ]; then \
				echo "// пропущен: файл слишком большой ($$file)"; \
				continue; \
			fi; \
			if file "$$file" | grep -q "text"; then \
				cat "$$file"; \
			else \
				echo "// пропущен: бинарный файл ($$file)"; \
			fi; \
			echo ""; \
			echo "// ---"; \
		fi; \
	done > txt.txt
	@echo "Done. Output written to txt.txt"

# Генерация документации через Doxygen
docs:
	@command -v doxygen >/dev/null 2>&1 || { echo "Doxygen not installed. Install with: sudo apt install doxygen"; exit 1; }
	doxygen Doxyfile
	@echo "Documentation generated in docs/html/"