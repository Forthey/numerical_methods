from myqt.default.default_window import *
from myqt.p3.p3_window import P3Window
from myqt.p4.p4_window import P4Window
from myqt.p5.p5_window import P5Window


class MainWindow(Window):
    def __init__(self):
        super().__init__(None)

        # Define available windows to switch
        self.p3_window = P3Window(self)
        self.p4_window = P4Window(self)
        self.p5_window = P5Window(self)

        # Define available button to click
        p3_button: Button = Button("3. Иллюстрация работы метода интерполяции полиномом")
        p3_button.on_click(self.p3_button_click)
        p4_button: Button = Button("4. Зависимость ошибки интерполяции от степени интерполяционного полинома")
        p4_button.on_click(self.p4_button_click)
        p5_button: Button = Button("5. Зависимость ошибки в выбранных точках от степени интерполяционного полинома")
        p5_button.on_click(self.p5_button_click)

        # Add widgets to layout
        self.layout.addWidget(p3_button, 1, 1, 2, 2, Qt.AlignmentFlag.AlignCenter)
        self.layout.addWidget(p4_button, 2, 1, 2, 2, Qt.AlignmentFlag.AlignCenter)
        self.layout.addWidget(p5_button, 3, 1, 2, 2, Qt.AlignmentFlag.AlignCenter)

    def p3_button_click(self):
        self.p3_window.show()
        self.hide()

    def p4_button_click(self):
        self.p4_window.show()
        self.hide()

    def p5_button_click(self):
        self.p5_window.show()
        self.hide()