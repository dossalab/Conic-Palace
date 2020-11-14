/*
 * Part of the Conic Palace - robot control center
 *
 * See LICENSE.md for licensing information
 * Roman Luitko, 2020
 */

package main

import (
	"github.com/gotk3/gotk3/gtk"
	"log"
)

func createLayout(window *gtk.Window) error {
	l, err := gtk.LabelNew("Hello, gotk3!")
	if err != nil {
		return err
	}

	window.Add(l)
	return nil
}

func main() {
	gtk.Init(nil)

	win, err := gtk.WindowNew(gtk.WINDOW_TOPLEVEL)
	if err != nil {
		log.Fatal("Unable to create window:", err)
	}

	createLayout(win)
	win.SetTitle("Simple Example")
	win.Connect("destroy", func() {
		gtk.MainQuit()
	})

	win.SetDefaultSize(800, 600)
	win.ShowAll()

	gtk.Main()
}
