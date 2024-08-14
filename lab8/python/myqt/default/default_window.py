from PyQt6.QtCore import Qt
from PyQt6.QtWidgets import *
from PyQt6.QtGui import QIcon
from myqt.default.default_button import Button


class Window(QWidget):
    def __init__(self, parent_window: QWidget | None):
        super().__init__()

        # set default window size
        self.resize(900, 600)
        self.setWindowTitle("Лаб 8: метод Лагранжа")
        self.setWindowIcon(QIcon("./img.png"))

        # define parent (previous) window
        self.parent_window = parent_window

        # Define layout and add default widgets to it
        self.layout = QGridLayout()
        self.setLayout(self.layout)

        # define default buttons
        back_button: Button = Button("Назад")
        back_button.setFixedWidth(40)
        back_button.setFixedHeight(20)
        back_button.on_click(self.go_back_to_parent_window)

        self.layout.addWidget(back_button, 0, 0, alignment=Qt.AlignmentFlag.AlignTop)

    def go_back_to_parent_window(self):
        if self.parent_window is not None:
            self.parent_window.show()
            self.close()
        else:
            self.hide()
