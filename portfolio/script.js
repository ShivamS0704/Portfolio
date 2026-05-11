window.addEventListener("load", () => {
  const preloader = document.getElementById("preloader");
  const percent = document.getElementById("preloaderPercent");
  const bar = document.getElementById("preloaderBar");

  let load = 0;
  const interval = setInterval(() => {
    load++;
    if (percent) percent.textContent = load + "%";
    if (bar) bar.style.width = load + "%";

    if (load >= 100) {
      clearInterval(interval);
      setTimeout(() => {
        if (preloader) {
          preloader.style.opacity = "0";
          preloader.style.visibility = "hidden";
          preloader.style.display = "none";
        }
      }, 300);
    }
  }, 15);

  const hamburger = document.getElementById("hamburger");
  const navLinks = document.getElementById("navLinks");

  if (hamburger && navLinks) {
    hamburger.addEventListener("click", () => {
      hamburger.classList.toggle("active");
      navLinks.classList.toggle("active");
    });
  }

  const typedText = document.getElementById("typedText");
  const words = [
    "C Programmer",
    "Future Software Engineer",
    "Problem Solver",
    "Tech Enthusiast"
  ];

  let wordIndex = 0;
  let charIndex = 0;
  let deleting = false;

  function type() {
    if (!typedText) return;

    const word = words[wordIndex];

    typedText.textContent = deleting
      ? word.substring(0, charIndex--)
      : word.substring(0, charIndex++);

    if (!deleting && charIndex === word.length + 1) {
      deleting = true;
      setTimeout(type, 1000);
      return;
    }

    if (deleting && charIndex === 0) {
      deleting = false;
      wordIndex = (wordIndex + 1) % words.length;
    }

    setTimeout(type, deleting ? 60 : 100);
  }

  type();

  const navbar = document.getElementById("navbar");
  const progress = document.getElementById("scrollProgress");
  const backTop = document.getElementById("backTop");

  window.addEventListener("scroll", () => {
    if (navbar) {
      navbar.classList.toggle("scrolled", window.scrollY > 50);
    }

    if (progress) {
      const height = document.documentElement.scrollHeight - window.innerHeight;
      progress.style.width = (window.scrollY / height) * 100 + "%";
    }

    if (backTop) {
      backTop.classList.toggle("show", window.scrollY > 500);
    }
  });

  if (backTop) {
    backTop.addEventListener("click", () => {
      window.scrollTo({ top: 0, behavior: "smooth" });
    });
  }

  const counters = document.querySelectorAll(".counter");
  let started = false;

  function startCounters() {
    if (started) return;

    counters.forEach(counter => {
      const target = Number(counter.dataset.target);
      let count = 0;

      const update = () => {
        count += target / 100;
        if (count < target) {
          counter.textContent = Math.ceil(count);
          requestAnimationFrame(update);
        } else {
          counter.textContent = target;
        }
      };

      update();
    });

    started = true;
  }

  window.addEventListener("scroll", () => {
    const about = document.getElementById("about");
    if (about && about.getBoundingClientRect().top < window.innerHeight - 100) {
      startCounters();
    }
  });

  const revealItems = document.querySelectorAll(
    ".reveal, .reveal-up, .reveal-left, .reveal-right, .section"
  );

  function revealOnScroll() {
    revealItems.forEach(item => {
      if (item.getBoundingClientRect().top < window.innerHeight - 100) {
        item.classList.add("show");
      }
    });
  }

  window.addEventListener("scroll", revealOnScroll);
  revealOnScroll();

  const form = document.getElementById("contactForm");
  const success = document.getElementById("formSuccess");

  if (form) {
    form.addEventListener("submit", e => {
      e.preventDefault();
      if (success) success.style.display = "block";
      form.reset();
    });
  }
});