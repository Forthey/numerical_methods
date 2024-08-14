from myqt.default.default_window import *


class PWindow(Window):
    def __init__(self, parent_window: Window | None):
        super().__init__(parent_window)

        # Define available windows to switch
        self.p_reader = ...
        self.p_analyzer = ...

        # Define available button to click
        compute_button: Button = Button("Создать файлы для расчёта")
        compute_button.on_click(self.go_to_reader_window)
        analyze_button: Button = Button("Анализ результатов")
        analyze_button.on_click(self.go_to_analyzer_window)

        # Define inputs
        self.input = QLineEdit()
        self.input.setFixedWidth(150)

        # Add widgets to layout
        self.layout.addWidget(compute_button, 1, 1, 2, 2, Qt.AlignmentFlag.AlignCenter)
        self.layout.addWidget(analyze_button, 2, 1, 2, 2, Qt.AlignmentFlag.AlignCenter)

    def go_to_reader_window(self):
        ...

    def go_to_analyzer_window(self):
        ...
